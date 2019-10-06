Dotenv.config();

let env = Node.Process.process##env;

let port = Js.Dict.unsafeGet(env, "EXPRESS_PORT");
