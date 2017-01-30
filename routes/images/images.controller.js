(function() {
    'use strict';

    var Image = require('./images.model');


//Basic CRUD
    
    //grab all for display
    module.exports.getAll = function(req, res) { 
        Image.find({}, function (err, post) {
            if (err) {
                console.error(err);
                return res.status(500).send(err);
            }
            res.json(post);
            
        });
    };

    
    //create a new post
    module.exports.create = function(req, res) {
        var image = new Image(req.body);
        image.save(function(err, post) {
          if (err) {
                console.error(err);
                return res.status(500).send(err);
          }
          res.json(post);
        });
     };
  
     //edit exsisting one
     module.exports.update = function(req, res) {
        var imageID = req.params.imageID;
        var body = req.body;
        // Need to do this so mongo doesn't think we're trying to edit the _id
        delete body._id;
        Image.findOneAndUpdate({_id: imageID}, req.body, function(err, post) {
          if (err) {
                console.error(err);
                return res.status(500).send(err);
          }  
          res.json(post);
        });
     };
    
    
})();