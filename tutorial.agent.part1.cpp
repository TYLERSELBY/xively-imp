const FEED_ID = "FEED_ID_HERE";
const API_KEY = "API_KEY_HERE";

function send_cosm(body) {         //take in csv value
    local cosm_url = "https://api.cosm.com/v2/feeds/" + FEED_ID + ".csv";       //setup url for csv
    server.log(cosm_url);
    server.log(body);       //pring body for testing
    local req = http.put(cosm_url, {"X-ApiKey":API_KEY, "Content-Type":"text/csv", "User-Agent":"Cosm-Imp-Lib/1.0"}, body);     //add headers
    local res = req.sendsync();         //send request
    if(res.statuscode != 200) {
        server.log("error sending message: "+res.body);
    }else device.send("status", (res.statuscode + " OK"));      //sends status to uart. this can be removed if not desired

}
 
device.on("data", function(feedCSV) {       //take csv body in from device
    server.log("device on");
    
    //send preformatted multi-ds csv
    send_cosm(feedCSV);         //send to function to call cosm
});