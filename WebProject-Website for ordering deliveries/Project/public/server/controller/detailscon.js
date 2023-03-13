var detailsdb = require('../model/detailsmodel');
var orderdb = require('../model/model');

//create and save new details
exports.create=(req,res)=>{ 
    if(!req.body){
        res.status(400).send({ message : "details can not be emtpy!"});
        return;
    }

    orderdb.find({}, (err, docs) => {
        if (err) {
          console.error(err);
          return;
        }
      
        // Convert the array of objects to a JSON string
        const orderData = JSON.stringify(docs);

        // new details
        const details = new detailsdb({
            Name : req.body.Name,
            Address : req.body.Address,
            PhoneNumber: req.body.PhoneNumber,
            Notice: req.body.Notice,
            Products: orderData
        })

        // save details in the database
    details
    .save(details)
    .then(data => {
        res.send(data)
        orderdb.deleteMany({}, (err) => {
            if (err) {
              console.error(err);
            } else {
              console.log('Collection cleared!');
            }
          });
    })
    .catch(err =>{
        res.status(500).send({
            message : err.message || "Some error occurred while creating a create operation"
        });
    });
});
}

//retrieve and return all details or a single details
exports.find=(req,res)=>{
    if(req.query.id){
        const id = req.query.id;
        detailsdb.findById(id)
        .then(data=>{
            if(!data){
                res.status(404).send({message:"Not found details with id" +id})
            }else{
                res.send(data)
            }
        })
        .catch(err=>{
            res.status(500).send({message:"Error retrieving details with id"+id})
        })

    }else{
        detailsdb.find().then(details=>{
            res.send(details)
        })
        .catch(Error =>{
            res.status(500).send({message:Error.message || "Error Occurred while retriving details details"})
        })
    }

}

//update a new details by details id
exports.update=(req,res)=>{
    if(!req.body){
        return res
        .status(400)
        .send({message:"Data to update can not be empty"})
    }

    const id = req.params.id;
    detailsdb.findByIdAndUpdate(id, req.body,{useFindAndModify:false})
    .then(data =>{
        if(!data){
            res.status(404).send({message:`Cannot update details with ${id}.Maybe user not found!`})
        }else{
            res.send(data)
        }
    })
    .catch(err=>{
        res.status(500).send({message:"Error Update details information"})
    })

}

//delete a details with specified details id in the request



exports.delete = (req, res)=>{
    const id = req.params.id;

    detailsdb.findByIdAndDelete(id)
        .then(data => {
            if(!data){
                const id = req.body.id;
                detailsdb.findByIdAndDelete(id).then(data =>{
                    if(!data){
                        res.status(404)("There is no orders with this id :" + id)
                    }
                })
                
                
            }else{
                res.send({
                    message : "order was deleted successfully!"
                })
            }
        })
        .catch(err =>{
            res.status(500).send({
                message: "Could not delete order with id=" + id
            });
        });
}