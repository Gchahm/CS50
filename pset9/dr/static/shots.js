d3.csv("static/2013-14_shots.csv", function(data){
 
    var shots = d3.select("svg")
        .selectAll("g")
            .data(data)
            .enter()
            .append("g")
                .attr("class", "shot")
                .attr("transform", function(d){
                    return "translate(" + 10 * d.converted_y + "," + 10 * d.converted_x + ")";
                })
            .on("mouseover", function(d){
                d3.select(this).raise()
                    .append("text")
                    .attr("class", "playername")
                    .text(d.player);
            })
            .on("mouseout", function(d){
                d3.selectAll("text.playername").remove();
            })
            
    shots.append("circle")
         .attr("r", 5)
         .attr("fill", function(d) {
            if (d.result == "made") {
                return "green";
            } else {
                return "red";
            }
        })
        
        
    var players = d3.nest()
       .key(function(d){ return d.player; })
        .rollup(function(a){ return a.length; })
        .entries(data);
    
    
        
    players.unshift({"key": "ALL", 
                     "value": d3.sum(players, function(d) { return d.value; })})
    

    var selector = d3.select("#selector");

    selector
         .selectAll("option")
         .data(players)
         .enter()
         .append("option")
             .text(function(d){ return d.key + ":" + d.value; })
             .attr("value", function(d){ return d.key; })
    
    selector
         .on("change", function(){
            d3.selectAll(".shot")
                .attr("opacity", 1.0);
             var value = selector.property("value");
            if (value != "ALL") {
                changeInfo(value) 
                 d3.selectAll(".shot")
                     .filter(function(d) { return d.player != value; })
                     .attr("opacity", 0.1);
            }
        })
    
    var playerInfoSection = d3.selectAll("#playerInfo");
    
    var missed=0;
    var made=0;
    var total=0;
    var distance=0;
    function changeInfo(player){

        var playerInfo = data.filter(function(p){
            if(p.player == player){
                total++;
                if(p.result == 'missed'){
                    missed++;
                }else if(p.result == 'made'){
                    made++;
                }
                distance = distance + parseFloat(p.distance);
            }
            return p.player == player;
        })
    
        console.log(playerInfo);
        playerInfoSection
            .selectAll("p")
            .data(["Name: " + player,"Total Shots: " + total,"Made: "+made,"Missed: "+missed,"Made/total Ratio: " +(made/total)])
            .enter()
            .append("p")
                .text(function(d){ 
                    return d;
            })
    }

})
