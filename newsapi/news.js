var url = 'http://newsapi.org/v2/everything?' +
    'q=Apple&' +
    'from=2020-08-16&' +
    'sortBy=popularity&' +
    'apiKey=8fee895405ef454f86a5ec4a0dc6a4d6';

var req = new Request(url);

fetch(req)
    .then(function(response) {
        console.log(response.json());
    })