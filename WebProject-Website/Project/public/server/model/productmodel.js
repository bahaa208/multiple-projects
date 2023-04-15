const mongoose = require('mongoose');

var schema = new mongoose.Schema({
    ProductName:String,
    Price:Number,
    Kind:String,
})

const productdb = mongoose.model('productdb',schema);

module.exports = productdb;