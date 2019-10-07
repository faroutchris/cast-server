[@bs.val] external setTimeout: (unit => unit, int) => float = "setTimeout";

let cb = f =>
  (. err, result) => {
    Belt.Result.(
      switch (err, result) {
      | (Some(err), None) => f(Error(err))
      | (None, Some(result)) => f(Ok(result))
      | _ => invalid_arg("Callback arguments invalid")
      }
    );
  };