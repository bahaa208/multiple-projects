const mongoose = require('mongoose');

var schema = new mongoose.Schema({
    ProductName:String,
    Price:{type:Number},
    Kind:String,
    Quantity:Number,
})

const orderdb = mongoose.model('orderdb',schema);

module.exports = orderdb;