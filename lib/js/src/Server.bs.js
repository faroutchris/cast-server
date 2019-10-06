// Generated by BUCKLESCRIPT VERSION 5.0.6, PLEASE EDIT WITH CARE
'use strict';

var Express = require("bs-express/lib/js/src/Express.js");
var Process = require("process");
var Config$CastServer = require("./Config.bs.js");
var Routes$CastServer = require("./Routes.bs.js");
var Caml_js_exceptions = require("bs-platform/lib/js/caml_js_exceptions.js");

var app = Express.express(/* () */0);

Express.App[/* use */0](app, Express.Middleware[/* json */0](undefined, undefined, undefined, /* () */0));

Express.App[/* get */4](app, "/", Routes$CastServer.IndexRoute[/* make */0]);

Express.App[/* post */9](app, "/command", Routes$CastServer.CommandRoute[/* make */0]);

function onListen(e) {
  var exit = 0;
  var val;
  try {
    val = e;
    exit = 1;
  }
  catch (raw_e){
    var e$1 = Caml_js_exceptions.internalToOCamlException(raw_e);
    console.log(e$1);
    Process.exit(1);
    return /* () */0;
  }
  if (exit === 1) {
    console.log("Listening at http://127.0.0.1:" + Config$CastServer.port);
    return /* () */0;
  }
  
}

Express.App[/* listen */21](app, 3000, onListen, /* () */0);

exports.app = app;
exports.onListen = onListen;
/* app Not a pure module */