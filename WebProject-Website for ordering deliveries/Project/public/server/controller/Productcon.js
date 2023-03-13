var productdb = require('../model/productmodel');

//create and save new product
exports.create=(req,res)=>{ 
    if(!req.body){
        res.status(400).send({ message : "Product details cant be empty!"});
        return;
    }

    // new order
    const product = new productdb({
        ProductName : req.body.ProductName,
        Price : req.body.Price,
        Kind: req.body.Kind
    })

    // save order in the database
    product
        .save(product)
        .then(data => {
            res.send(data)
        })
        .catch(err =>{
            res.status(500).send({
                message : err.message || "Some error occurred while creating a create operation"
            });
        });
}


//retrieve and return all products or a single order
exports.find=(req,res)=>{
    if(req.query.id){
        const id = req.query.id;
        productdb.findById(id)
        .then(data=>{
            if(!data){
                res.status(404).send({message:"Not found product with id" +id})
            }else{
                res.send(data)
            }
        })
        .catch(err=>{
            res.status(500).send({message:"Error retrieving product with id"+id})
        })

    }else{
        productdb.find().then(product=>{
            res.send(product)
        })
        .catch(Error =>{
            res.status(500).send({message:Error.message || "Error Occurred while retriving product details"})
        })
    }

}


//update a new product by order id
exports.update=(req,res)=>{
    if(!req.body){
        return res
        .status(400)
        .send({message:"Data to update can not be empty"})
    }

    const id = req.params.id;
    productdb.findByIdAndUpdate(id, req.body,{useFindAndModify:false})
    .then(data =>{
        if(!data){
            res.status(404).send({message:`Cannot update order with ${id}.Maybe user not found!`})
        }else{
            res.send(data)
        }
    })
    .catch(err=>{
        res.status(500).send({message:"Error Update order information"})
    })

}

//delete a product with specified order id in the request
exports.delete = (req, res)=>{
    const id = req.params.id;

    productdb.findByIdAndDelete(id)
        .then(data => {
            if(!data){
                const id = req.body.id;
                productdb.findByIdAndDelete(id).then(data =>{
                    if(!data){
                        res.status(404)("There is no product with this id :" + id)
                    }
                })
                
                
            }else{
                res.send({
                    message : "product was deleted successfully!"
                })
            }
        })
        .catch(err =>{
            res.status(500).send({
                message: "Could not delete product with id=" + id
            });
        });
}

