type t;
type url = string;
type nullable('a) = Js.null('a);
type err = nullable(Js.Exn.t);
type cb('a) = (err, nullable('a)) => unit;

type cbh('b) = (. option(Js.Exn.t), option('b)) => unit;

[@bs.module] external make: unit => t = "chromecast-player-reloaded";

type callbackResultType('a, 'b) = Belt.Result.t('b, 'a);

[@bs.send]
external launch:
  (t, url, (. option(exn), option(t)) => unit) =>
  Js.Promise.t(Belt.Result.t('a, exn)) =
  "launch";

// Init
// [@bs.send]
// external launch: (t, url, (. option(exn), option(t)) => unit) => unit =
//   "launch";

[@bs.send]
external attach: (t, url, (. option(exn), option(t)) => unit) => unit =
  "attach";

// session controls
[@bs.send] external play: (t, cb('a)) => unit = "play";
[@bs.send] external pause: (t, cb('a)) => unit = "pause";
[@bs.send] external stop: (t, cb('a)) => unit = "stop";
[@bs.send] external seek: (t, int) => unit = "seek";

// platform controls
[@bs.send] external setVolume: (t, cb(int)) => unit = "setVolume";
[@bs.send] external getVolume: (t, cb(int)) => unit = "getVolume";
[@bs.send] external mute: t => unit = "mute";
[@bs.send] external unmute: t => unit = "unmute";

// Timeline getters
[@bs.send] external getPosition: (t, float) => unit = "getPosition";
[@bs.send] external getProgress: (t, float) => unit = "getProgress";

// Event listeners
[@bs.deriving jsConverter]
type event = [ | `playing | `closed | `status | `position];

[@bs.send] external once: (t, string, Js.t('a) => unit) => unit = "once";
[@bs.send] external on: (t, string, Js.t('a) => unit) => unit = "on";

// convenience functions
let player = make();
let launchPlayer = launch(player);
let attachPlayer = attach(player);

// let promisifiedLaunch = url => {
//   let r =
//     launchPlayer(
//       url,
//       (. err, result) => {
//         Js.log4("err", err, "result", result);
//         switch (err, result) {
//         | (Some(e), None) => Belt.Result.Error(e)
//         | (None, Some(result)) => Belt.Result.Ok(result)
//         | (_, _) => Belt.Result.Error("s"->failwith)
//         };
//       },
//     );
//   Js.log(r);
//   Js.Promise.resolve(r);
// };

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

/*
 // const promisified = (arg) => {
 //   return new Promise((reject, resolve) => {
 //     myDb(arg, (err, db) => {
 //       if (err) reject(err);
 //       resolve(db);
 //       // return undefined*/