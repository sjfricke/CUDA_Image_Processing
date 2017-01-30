//-------------------------Module "Importing"-----------------------------//
var express = require('express'); //used as routing framework
var app = express(); //creates an instance of express

//modules required (same idea of #includes or Imports)
var path = require('path'); //Node.js module used for getting path of file
var logger = require('morgan'); //used to log in console window all request
var cookieParser = require('cookie-parser'); //Parse Cookie header and populate req.cookies
var bodyParser = require('body-parser'); //allows the use of req.body in POST request
var server = require('http').createServer(app); //creates an HTTP server instance

var multer  = require('multer'); //used for getting uploaded files
var upload = multer({ dest: 'uploads/' });
var fs = require('fs');

var api = require('./routes/api'); //gets api logic from path

//-------------------------MongoDB Setup-----------------------------//
var mongoose = require('mongoose');            
var image_model = require('./routes/images/images.model'); //used to upload data with image
var mongoURI = "mongodb://127.0.0.1:27017/CUDA_Image_Processing";
var MongoDB = mongoose.connect(mongoURI).connection;
MongoDB.on('error', function(err) { console.log(err.message); });
MongoDB.once('open', function() {
    console.log("mongodb connection open");
});

//-------------------------Globals-----------------------------//
var localIP = require("ip").address(); //used to know where to check for web view site
console.log("Local IP: " + localIP);

var debugMode = false;
//-------------------------Node Setup-----------------------------//
//Loops through starting after "node server.js" and checks the arguments
for (var i = 2; i < process.argv.length; i++) {
    switch(process.argv[i]){
        case "-debug":
            console.log("RUNNING IN DEBUG MODE");
            debugMode = true;
    }
}

//-------------------------Express JS configs-----------------------------//
//view engine setup

app.use(logger('dev')); //debugs logs in terminal
app.use(bodyParser.json()); //parses json and sets to body
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'front'))); //sets all static file calls to folder


//---------------API-------------------//
app.use('/api', api);


app.get('/', function(req, res, next) {
  res.sendFile('index.html');
});

/*
fileName: String,
displayName: String,
thumbnailPath: String,
originialPath: String,
colorInfoPath: String,
filetype: String,
width: Number,
height: Number
*/

app.post('/fileUpload', upload.single('file'), function(req, res) {
    
    //new name
    var filePath = __dirname + '/uploads/' + req.file.filename + req.file.originalname.substr(req.file.originalname.lastIndexOf('.'));
    
    console.log("filePaht " + filePath);
    
    //prevents duplicate files
    if (fs.existsSync(filePath)) {
        filePath += Date.now();
    }
    
    fs.rename(req.file.path, filePath, function(err) {
        if (err) {
            console.error(err);
            res.send(500);
        } else {
        
            res.send("TODO");            
        }
    });
});


// catch 404 and forward to error handler
/*app.use(function(req, res, next) {
  var err = new Error('Not Found');
  err.status = 404;
  next(err); 
});*/

// error handlers
/*app.use(function(err, req, res, next) {
    res.status(err.status || 500);
    res.render('error', {
      message: err.message,
      error: err
    });
});*/



// ------------ Server Setup --------------//


/**
 * Get port from environment and store in Express.
 */
var port = normalizePort(process.env.PORT || '9000');
app.set('port', port);

/**
 * Create HTTP server.
 */
//done up top

/**
 * Listen on provided port, on all network interfaces.
 */

server.listen(port);
server.on('error', onError);
server.on('listening', onListening);

/**
 * Normalize a port into a number, string, or false.
 */

function normalizePort(val) {
  var port = parseInt(val, 10);

  if (isNaN(port)) {
    // named pipe
    return val;
  }

  if (port >= 0) {
    // port number
    return port;
  }

  return false;
}

/**
 * Event listener for HTTP server "error" event.
 */

function onError(error) {
  if (error.syscall !== 'listen') {
    throw error;
  }

  var bind = typeof port === 'string'
    ? 'Pipe ' + port
    : 'Port ' + port;

  // handle specific listen errors with friendly messages
  switch (error.code) {
    case 'EACCES':
      console.error(bind + ' requires elevated privileges');
      process.exit(1);
      break;
    case 'EADDRINUSE':
      console.error(bind + ' is already in use');
      process.exit(1);
      break;
    default:
      throw error;
  }
}

/**
 * Event listener for HTTP server "listening" event.
 */

function onListening() {
  var addr = server.address();
  var bind = typeof addr === 'string'
    ? 'pipe ' + addr
    : 'port ' + addr.port;
  console.log('Listening on ' + bind);
}
