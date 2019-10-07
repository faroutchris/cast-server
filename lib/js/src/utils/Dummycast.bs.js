// Generated by BUCKLESCRIPT VERSION 5.0.6, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var DummyCastJs = require("./../../../../src/dummyCast.js");

function make(prim) {
  return DummyCastJs();
}

var player = DummyCastJs();

function launchPlayer(param, param$1) {
  return player.launch(param, param$1);
}

function promisifiedLaunch(url) {
  return new Promise((function (resolve, _r) {
                player.launch(url, (function (err, result) {
                        var result$1 = err !== undefined ? (
                            result !== undefined ? /* Error */Block.__(1, [Pervasives.failwith("s")]) : /* Error */Block.__(1, [err])
                          ) : (
                            result !== undefined ? /* Ok */Block.__(0, [Caml_option.valFromOption(result)]) : /* Error */Block.__(1, [Pervasives.failwith("s")])
                          );
                        return resolve(result$1);
                      }));
                return /* () */0;
              }));
}

exports.make = make;
exports.player = player;
exports.launchPlayer = launchPlayer;
exports.promisifiedLaunch = promisifiedLaunch;
/* player Not a pure module */