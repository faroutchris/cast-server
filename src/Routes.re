open Express;
open Js.Promise;

let successResponse = () => {
  let json = Js.Dict.empty();
  Js.Dict.set(json, "success", Js.Json.boolean(true));
  Response.sendJson(Js.Json.object_(json));
};

let badRequest = Response.sendStatus(BadRequest);

module IndexRoute = {
  let make = Middleware.from((_, _, res) => res |> successResponse());
};

module CommandRoute = {
  let make =
    PromiseMiddleware.from((_next, req, res) =>
      switch (req |> Request.bodyJSON) {
      | None => res |> badRequest |> resolve
      | Some(body) =>
        let {command, payload}: Decode.Command.t =
          body |> Decode.Command.make;

        switch (command) {
        | "launch" => Sender.launch(payload)
        | "play" => Sender.play
        | "pause" => Sender.pause
        | "stop"
        | "mute"
        | "unmute"
        | "setVolume"
        | _ => Js.Promise.resolve() |> ignore
        };

        res |> successResponse() |> resolve;
      }
    );
};