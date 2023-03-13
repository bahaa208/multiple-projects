const bar = document.getElementById('bar');
const close = document.getElementById('close');
const nav = document.getElementById('navbar');

if(bar){
    bar.addEventListener('click', () => {
        nav.classList.add('active');

    })

}


if(close){
    close.addEventListener('click', () => {
        nav.classList.remove('active');

    })

}


function Add_details(){
    
    // Get the input data
    const Name1 = document.getElementById('Name').value;
    const Address1 = document.getElementById('Address').value;
    const PhoneNumber1 = document.getElementById('PhoneNumber').value;
    const Notice1 = document.getElementById('Notice').value;


    

    // Send the form data to the server using an AJAX request
    var xhr = new XMLHttpRequest();
    xhr.open("POST", "/api/details",true);
    xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xhr.send("Name=" + encodeURIComponent(Name1) + "&Address=" + encodeURIComponent(Address1) + "&PhoneNumber=" + encodeURIComponent(PhoneNumber1) + "&Notice=" + encodeURIComponent(Notice1));


    window.location.href = "/";
    alert("Order added successfuly!");
}

function addToCart(productName, kind, price, quantity)
{
    // Send the form data to the server using an AJAX request
    var xhr = new XMLHttpRequest();
    xhr.open("POST", "/api/orders");
    xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xhr.send("ProductName=" + encodeURIComponent(productName) + "&Kind=" + encodeURIComponent(kind) + "&Price=" + encodeURIComponent(price) + "&Quantity=" + encodeURIComponent(quantity));

    alert("Product added successfuly!");
}


function removeFromCart(id){

    const xhr = new XMLHttpRequest();
    xhr.open('DELETE', '/api/orders/' + id);
    xhr.setRequestHeader('Authorization', 'Bearer <access_token>');
    xhr.send();
    xhr.addEventListener('load', () => {
        if (xhr.status === 200) {
          alert('Product deleted successfully!');
          location.reload();
        } else {
          alert('An error occurred while deleting product.');
        }
    });
      


}


function removeFromUpdateDetails(products,id,id2){

    const productsArray = JSON.parse(products);

    const updatedProductsArray = productsArray.filter(product => product._id !== id);

    const productsJson = JSON.stringify(updatedProductsArray);

    var xhr = new XMLHttpRequest();
    xhr.open('PUT', '/api/details/' + id2 , true);
    xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xhr.send("Products=" + encodeURIComponent(productsJson));

    location.reload();
    
    
    
}



function saveUpdatedDetails(id){

    // Get the input data
    const Name1 = document.getElementById('Name2').value;
    const Address1 = document.getElementById('Address2').value;
    const PhoneNumber1 = document.getElementById('PhoneNumber2').value;
    const Notice1 = document.getElementById('Notice2').value;


    

    // Send the form data to the server using an AJAX request
    var xhr = new XMLHttpRequest();
    xhr.open("PUT", "/api/details/" + id,true);
    xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xhr.send("Name=" + encodeURIComponent(Name1) + "&Address=" + encodeURIComponent(Address1) + "&PhoneNumber=" + encodeURIComponent(PhoneNumber1) + "&Notice=" + encodeURIComponent(Notice1));

    window.location.href = "/orders";
    alert("Order Updated Successfuly!!");
}



function removeFromOrders(id){

    const xhr = new XMLHttpRequest();
    xhr.open('DELETE', '/api/details/' + id);
    xhr.setRequestHeader('Authorization', 'Bearer <access_token>');
    xhr.send();
    xhr.addEventListener('load', () => {
        if (xhr.status === 200) {
          alert('Order deleted successfully!');
          location.reload();
        } else {
          alert('An error occurred while deleting product.');
        }
    });

}