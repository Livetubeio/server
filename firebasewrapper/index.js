var app = require('express')();
var http =  require('http').Server(app);
var io = require('socket.io')(http);
var firebase = require('firebase');

var config = {
    apiKey: process.env.FIREBASE_API,
    authDomain: "livetubeio-16323.firebaseapp.com",
    databaseURL: "https://livetubeio-16323.firebaseio.com/",
};
firebase.initializeApp(config);

io.on('connection', (socket) => {
    socket.on('updateChannel', (path, data) => {
        firebase.database().ref(path).update(JSON.parse(data));
    })
    console.log("server connected");
});

http.listen(3000, 'localhost', () => {
   console.log("listening on port %d", http.address().port);
})