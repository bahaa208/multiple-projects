const mongoose = require('mongoose');

const connectDB = async()=>{
    try {
        const con = await mongoose.connect(process.env.MONGO_URI,{
            
        })

        console.log(`MongoDB connected:${con.connection.host}`);
    } catch (error) {
        console.log(error);
        process.exit(1);
    }
}

mongoose.set('strictQuery', false);
module.exports = connectDB