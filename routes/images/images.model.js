(function() {
    'use strict';

    var mongoose = require('mongoose');
    var Schema = mongoose.Schema;

    var ImageSchema = new Schema({
        fileName: String,
        thumbnail: String,
        full: String,
        image_id: Number
    }, 
    { collection : 'images' }
    );
    
module.exports = mongoose.model('Image', ImageSchema);

})();