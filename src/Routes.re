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
  open Common;

  let make =
    PromiseMiddleware.from((_next, req, res) =>
      switch (req |> Request.bodyJSON) {
      | None => res |> badRequest |> resolve
      | Some(body) =>
        let {command, payload}: Decode.Command.t =
          body |> Decode.Command.make;

        switch (command) {
        | "launch" =>
          Chromecast.launchPlayer(
            payload,
            cb(
              fun
              | Error(e) => Js.log(e)
              | Ok(p) => Js.log2("--->", p),
            ),
          )
        | "play"
        | "pause"
        | "stop"
        | "mute"
        | "unmute"
        | "setVolume"
        | _ => Js.Exn.raiseError("Unknown command")
        };

        res |> successResponse() |> resolve;
      }
    );
};
