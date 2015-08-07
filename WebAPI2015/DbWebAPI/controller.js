
// Master  Module
var app = angular.module('DemoApp', []);


// Master Portal Controller
var DemoController = function ($scope, $http, $compile, $window, $rootScope, $q, DemoService) {

};

// Service definition for all web service requests to the RA+ API
app.factory('DemoService', ['$http', '$location', function ($http, $location) {
    return {
        getBaseUrl: function () {
            return '/product';
        },
        deleteProductUrl: function (productCode) {
            return this.getBaseUrl() + '/' + productCode;
        },
        getProducts: function (successCallback, errorCallback) {
            $http({ method: 'GET', url: this.getBaseUrl() })
                .success(function (data, status, headers, config) {
                    successCallback(data, status, headers, config);
                })
                .error(function (data, status, headers, config) {
                    errorCallback();
                });
        },
        deleteProduct: function (productCode, successCallback, errorCallback) {
            $http({ method: 'DELETE', url: this.deleteProductUrl(productCode) })
                .success(function (data, status, headers, config) {
                    successCallback(data, status, headers, config);
                })
                .error(function (data, status, headers, config) {
                    errorCallback();
                });
        },
        addProduct: function(product, successCallback, errorCallback) {
            $http({ method: 'POST', url: this.getBaseUrl(), data: product })
                .success(function(data, status, headers, config) {
                    successCallback(data, status, headers, config);
                })
                .error(function(data, status, headers, config) {
                    errorCallback();
                });
        },
        updateProduct: function (product, successCallback, errorCallback) {
                $http({ method: 'PUT', url: this.getBaseUrl(), data: product })
                    .success(function (data, status, headers, config) {
                        successCallback(data, status, headers, config);
                    })
                    .error(function (data, status, headers, config) {
                        errorCallback();
                    });
        }
    };
}]);



