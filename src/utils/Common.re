[@bs.val] external setTimeout: (unit => unit, int) => float = "setTimeout";

let cb = f =>
  (. err, result) => {
    Js.Result.(
      switch (err, result) {
      | (Some(err), None) => f(Error(err))
      | (None, Some(result)) => f(Ok(result))
      // Throw if APIs break nodeback 'guarantee':
      | _ => invalid_arg("Nodeback arguments invalid")
      }
    );
  };
