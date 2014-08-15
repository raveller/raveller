
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
            var getUrl = this.getBaseUrl() + 'product/v2';
            return getUrl;
        },
        getProducts: function (successCallback, errorCallback) {
            $http({ method: 'GET', url: this.getProductsUrl() })
                .success(function (data, status, headers, config) {
                    successCallback(data, status, headers, config);
                })
                .error(function (data, status, headers, config) {
                    errorCallback();
                });
        },
        checkSessionUrl: function () {
            var getUrl = this.getBaseUrl() + 'check/v2';
            return getUrl;
        },
        checkSession: function (successCallback, errorCallback) {
            $http({ method: 'GET', url: this.checkSessionUrl() })
                .success(function (data, status, headers, config) {
                    successCallback(data, status, headers, config);
                })
                .error(function (data, status, headers, config) {
                    errorCallback();
                });
        },
        postLoginUrl: function () {
            var getUrl = this.getBaseUrl() + 'login/v2';
            return getUrl;
        },
        postLogin: function (login, successCallback, errorCallback) {
            $http({ method: 'POST', url: this.postLoginUrl(), data: login})
                .success(function (data, status, headers, config) {
                    successCallback(data, status, headers, config);
                })
                .error(function (data, status, headers, config) {
                    errorCallback();
                });
        },
        deleteLogoutUrl: function () {
            var getUrl = this.getBaseUrl() + 'logout/v2';
            return getUrl;
        },
        deleteLogout: function (successCallback, errorCallback) {
            $http({ method: 'DELETE', url: this.deleteLogoutUrl() })
                .success(function (data, status, headers, config) {
                    successCallback(data, status, headers, config);
                })
                .error(function (data, status, headers, config) {
                    errorCallback();
                });
        }
    };
}]);



