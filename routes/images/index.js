(function() {
    'use strict';

    var express = require('express');
    var controller = require('./images.controller');

    var router = express.Router();

    router.get('/getAll', controller.getAll);
    router.post('/new', controller.create);
    router.put('/update/:imageID', controller.update);
    //router.delete('/delete', controller.delete);

    module.exports = router;

})();
