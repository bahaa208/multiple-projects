const mongoose = require('mongoose');

var schema = new mongoose.Schema({
    Name:String,
    Address:String,
    PhoneNumber:String,
    Notice:String,
    Products: mongoose.Schema.Types.Mixed
})

const detailsdb = mongoose.model('detailsdb',schema);

module.exports = detailsdb;