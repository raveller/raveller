
// Master  Module
var app = angular.module('DemoApp', []);


// Master Portal Controller
var DemoController = function ($scope, $http, $compile, $window, $rootScope, $q, DemoService) {

    // Scope-level hook to call  API functions 
    $scope.callGetEdi = function (callback) {
        return DemoService.getEdi(callback);
    };
};

// Service definition for all web service requests to the RA+ API
app.factory('DemoService', ['$http', '$location', function ($http, $location) {
    return {
        getBaseUrl: function () {
            if (window.location.host == "localhost:30066")
                return '';

            return 'http://huck001.azurewebsites.net/';
        },
        getProductsUrl: function () {
            var getUrl = this.getBaseUrl() + 'product/v1';
            return getUrl;
        },
        getProducts: function (successCallback, errorCallback) {
            $http({ method: 'GET', url: this.getProductsUrl(), Accept: 'application/json' })
                .success(function (data, status, headers, config) {
                    successCallback(data, status, headers, config);
                })
                .error(function (data, status, headers, config) {
                    errorCallback();
                });
        }
    };
}]);



