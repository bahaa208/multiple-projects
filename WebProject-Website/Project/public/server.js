const express = require('express');
const dotenv = require('dotenv');
const path = require('path');
const morgan = require('morgan');
const bodyparser = require("body-parser");


const { connect } = require('http2');

const app = express();

const connectDB = require('./server/database/connection');
const orderdb = require('./server/model/model');
const product = require('./server/model/productmodel');
const detailsdb = require('./server/model/detailsmodel');
const { route } = require('./server/routes/router');
var control = require('./server/controller/controller');

dotenv.config({path:`views/config.env`})
const PORT = process.env.PORT || 8080

//log requests
app.use(morgan('tiny'));

//parse request to body-parser
app.use(bodyparser.urlencoded({extended:true}));



//set view engine
app.set("view engine","ejs")

//load assets
app.use('/css',express.static(path.resolve(__dirname,"assets/css")))
app.use('/img',express.static(path.resolve(__dirname,"assets/img")))
app.use('/js',express.static(path.resolve(__dirname,"assets/js")))

//mongodb connection
connectDB();

//load routers
app.use('/',require('./server/routes/router'))


app.post('/remove_product',function(req,res){

    control.delete(req,res);
});


app.listen(PORT, ()=>{console.log(`Server is running on http://localhost:${PORT}`)});