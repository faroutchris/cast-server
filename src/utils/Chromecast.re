type t;
type url = string;
type nullable('a) = Js.null('a);
type err = nullable(Js.Exn.t);
type cb('a) = (err, nullable('a)) => unit;

type cbh('b) = (. option(Js.Exn.t), option('b)) => unit;

// TODO: https://dev.to/yawaramin/how-to-handle-a-nodeback-in-reasonml-in7

[@bs.module] external make: unit => t = "chromecast-player-reloaded";

// Init
[@bs.send] external launch: (t, url, cbh(t)) => unit = "launch";

[@bs.send]
external attach: (t, url, (err, nullable(t)) => unit) => unit = "attach";

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
