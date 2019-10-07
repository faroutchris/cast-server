module.exports = () => ({
    launch: (mediaUrl, callback) => {
        if (mediaUrl === "fail") {
            return callback("Failure");
        }

        return callback(undefined, {
            player: "Dummycast"
        });
    }
})
