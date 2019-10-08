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
        | "launch" =>
          Chromecast.Methods.launch(payload)
          |> Js.Promise.then_(result => {
               switch (result) {
               | Belt.Result.Error(e) => Js.log2("-->", e)
               | Ok(player) => Js.log2("-->", player)
               };
               Js.Promise.resolve();
             })
          |> ignore
        | "play" =>
          Chromecast.Methods.(
            attach()
            |> Js.Promise.then_(result => {
                 switch (result) {
                 | Belt.Result.Error(e) => Js.log2("-->", e)
                 | Ok(player) =>
                   play(player)
                   |> Js.Promise.then_(player => {
                        switch (player) {
                        | Belt.Result.Error(e) => Js.log2("Error", e)
                        | Ok(status) => Js.log2("Status", status)
                        };

                        Js.Promise.resolve();
                      })
                   |> ignore
                 };

                 Js.Promise.resolve();
               })
            |> ignore
          )
        | "pause" =>
          Chromecast.Methods.(
            attach()
            |> Js.Promise.then_(result => {
                 switch (result) {
                 | Belt.Result.Error(e) => Js.log2("-->", e)
                 | Ok(player) =>
                   pause(player)
                   |> Js.Promise.then_(player => {
                        switch (player) {
                        | Belt.Result.Error(e) => Js.log2("Error", e)
                        | Ok(status) => Js.log2("Status", status)
                        };

                        Js.Promise.resolve();
                      })
                   |> ignore
                 };

                 Js.Promise.resolve();
               })
            |> ignore
          )
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
