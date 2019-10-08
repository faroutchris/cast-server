type t;
type url = string;
type nullable('a) = Js.null('a);
type err = nullable(Js.Exn.t);
type cb('a) = (err, nullable('a)) => unit;

[@bs.module] external make: unit => t = "chromecast-player-reloaded";

type callbackResultType('a, 'b) = Belt.Result.t('b, 'a);

[@bs.send]
external launch:
  (t, url, (. option(exn), option(t)) => unit) =>
  Js.Promise.t(Belt.Result.t('a, exn)) =
  "launch";

[@bs.send]
external attach:
  (t, (. option(exn), option(t)) => unit) =>
  Js.Promise.t(Belt.Result.t('a, exn)) =
  "launch";

// session controls
[@bs.send]
external play:
  (t, (. option(exn), option(t)) => unit) =>
  Js.Promise.t(Belt.Result.t('a, exn)) =
  "play";

[@bs.send]
external pause:
  (t, (. option(exn), option(t)) => unit) =>
  Js.Promise.t(Belt.Result.t('a, exn)) =
  "pause";

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

module Methods = {
  let launch = url => {
    Js.Promise.make((~resolve, ~reject as _r) =>
      launch(
        make(),
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
  };

  let attach = () => {
    Js.Promise.make((~resolve, ~reject as _r) =>
      attach(
        make(),
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
  };

  let play = player => {
    Js.Promise.make((~resolve, ~reject as _r) =>
      play(
        player,
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
  };

  let pause = player => {
    Js.Promise.make((~resolve, ~reject as _r) =>
      pause(
        player,
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
  };
};
