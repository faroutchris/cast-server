open Express;

let app = express();

App.use(app, Middleware.json());

App.get(app, ~path="/") @@ Routes.IndexRoute.make;

App.post(app, ~path="/command") @@ Routes.CommandRoute.make;

let onListen = e => {
  switch (e) {
  | exception e =>
    Js.log(e);
    Node.Process.exit(1);
  | _ => Js.log("Listening at http://127.0.0.1:" ++ Config.port)
  };
};

App.listen(app, ~port=3000, ~onListen, ());
