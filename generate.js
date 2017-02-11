/*
* Used to generate images for testing
* images of single color values are easier to examine
*/
Jimp = require("jimp");

//-------------------------MongoDB Setup-----------------------------//
var mongoose = require('mongoose');
var image_model = require('./routes/images/images.model'); //used to upload data with image
var mongoURI = "mongodb://127.0.0.1:27017/CUDA_Image_Processing";
mongoose.Promise = global.Promise; //Mongoose deprecated default promises (mpromise)
var MongoDB = mongoose.connect(mongoURI).connection;
MongoDB.on('error', function(err) { console.log(err.message); });
MongoDB.once('open', function() {
    console.log("mongodb connection open");
});

var HEIGHT = 576 || process.argv[2];
var WIDTH = 1024 || process.argv[3];
var image_buffer = new Array(128);
var current_color = 0x000000FF; // black full alpha
var color_stride =  0x02010000; // 0x000000 - 0xFF0F00
var image_count = 0;
var print_out = "";

var arr = Array.apply(null, Array(128)); // a sloppy way to use forEach()

arr.forEach(function(element, index) {

    // creates mongo item
    // note no thumbnail is written too
    image_buffer[index] = {
	"fileName": index + "_generated",
	"thumbnailPath": "server_images/thumbnail/" + index + "_generated.png",
	"originialPath": "server_images/full/" + index + "_generated.png",
	"mimetype": "image/png"
    };
    
    var image = new Jimp(WIDTH, HEIGHT, current_color + (color_stride * index), function (err, image) {
    	image.write("front/" + image_buffer[index].originialPath, function(){

	    // creates data for database
	    var image_document = new image_model(image_buffer[index]);

	    // saves it to database
	    image_document.save(function(err, post) {
		if (err) {
		    console.error(err);
		}
		print_out += (image_buffer[index].originialPath + " ");
		image_count++; //hoping node is thread safe
		if (image_count >= 127) end_generate(); 
	    });
	}); //image.write
    }); //new Jimp
}); //foreach


function end_generate() {
    console.log(print_out);
    process.exit(0);
}
