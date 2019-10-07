type t;
type url = string;

type cbh('b) = (. option(Js.Exn.t), option('b)) => unit;

[@bs.module] external make: unit => t = "./../../../../src/dummyCast.js";

// Init

[@bs.send]
external launch:
  (t, url, (. option(exn), option(t)) => unit) =>
  Js.Promise.t(Belt.Result.t('a, exn)) =
  "launch";

let player = make();
let launchPlayer = launch(player);

let promisifiedLaunch = url => {
  let promise =
    Js.Promise.make((~resolve, ~reject as _r) =>
      launchPlayer(
        url,
        (. err, result) => {
          let result =
            switch (err, result) {
            | (Some(e), None) => Belt.Result.Error(e)
            | (None, Some(result)) => Belt.Result.Ok(result)
            | (_, _) => Belt.Result.Error("s"->failwith)
            };
          resolve(. result);
        },
      )
      ->ignore
    );
  promise;
};