let launch = payload =>
  Chromecast.Methods.launch(payload)
  |> Js.Promise.then_(result => {
       switch (result) {
       | Belt.Result.Error(e) => Js.log2("-->", e)
       | Ok(player) => Js.log2("-->", player)
       };
       Js.Promise.resolve();
     })
  |> ignore;

let play =
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
  );

let pause =
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
  );