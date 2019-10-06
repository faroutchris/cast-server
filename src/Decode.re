module Command = {
  type t = {
    command: string,
    payload: string,
  };

  let make = json => {
    Json.Decode.{
      command: json |> field("command", string),
      payload: json |> field("payload", string),
    };
  };
};
