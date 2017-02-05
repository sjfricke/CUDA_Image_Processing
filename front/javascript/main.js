function init() {    
    $.get("/api/images/getAll", function(data) {
        
        console.log(data);
       
        var displayDOM = document.getElementById('display');
        
        data.forEach(function(element, index){           
                        
            let image_element = document.createElement("IMG");
            image_element.src = element.thumbnailPath;
                        
            let a_element = document.createElement('a');
            a_element.appendChild(image_element);
            a_element.setAttribute("class", "fancybox");
            a_element.rel = "group";
            a_element.href = element.originialPath;
            
            a_element.appendChild(image_element);
            displayDOM.appendChild(a_element);     
            
        });
        
    })
}

function test(file) {
    window.open('server_images/full/' + file);
}

$(document).ready(function() {
    $(".fancybox").fancybox();
});


//last thing to get called to kick off code
init();
