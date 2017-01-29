(function() {
  'use strict';

  var express = require('express');
  var controller = require('./images.controller')    
    
  var router = express.Router();

  router.get('/getAll', controller.getAll);  

  module.exports = router;

})();