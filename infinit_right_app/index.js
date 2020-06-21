const InfinitCore = require("./build/Debug/InfinitRight.node")
const io = require("socket.io")(420)


io.on("connection", socket => {
  console.log("connection")
  socket.on("corecall", (command, cb) => {
    cb(InfinitCore.CallCoreFunction(command))
  })

  InfinitCore.RegisterCallbackFn((args) => {
    console.log("changecallback: ", args);
    socket.emit("callback", args)
  })
})

