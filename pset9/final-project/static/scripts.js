$(document).ready(function(){
    $(".main-form").on("submit",function(){
        url = "https://ide50-gcham.cs50.io/search?location=dublin&country=ireland";
        update();
        return false;
    });
});

function getQUery(url){
  $.ajax({
      url: url,
      type: 'get',
      dataType: 'jsonp',
      success: alert("roda"),
      fail: alert("fail")
  })};
  
function update() 
{

    // get places within bounds (asynchronously)
    var parameters = {
        location : $("#location").val(),
        country : $("#country").val()

    };
    $.getJSON(Flask.url_for("search"),parameters)
    .done(function(data, textStatus, jqXHR) {
        alert(data);
    })
    .fail(function(jqXHR, textStatus, errorThrown) {

        // log error to browser's console
        console.log(errorThrown.toString());
    });
};