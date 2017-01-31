(function() {
    'use strict';

    var mongoose = require('mongoose');
    var Schema = mongoose.Schema;

    var ImageSchema = new Schema({
        fileName: String,
        displayName: String,
        thumbnailPath: String,
        originialPath: String,
        dataPath: String,
        mimetype: String,
        width: Number,
        height: Number
    },
    { collection : 'images' }
    );

module.exports = mongoose.model('Image', ImageSchema);

})();
