var simpleCast = require("simple-cast").default;
simpleCast.init();
simpleCast.send(
  "http://commondatastorage.googleapis.com/gtv-videos-bucket/CastVideos/dash/BigBuckBunnyVideo.mp4"
);
