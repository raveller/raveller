﻿
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
            var getUrl = this.getBaseUrl() + 'product/v3';
            return getUrl;
        },
        getProducts: function (successCallback, errorCallback) {
            $http({ method: 'GET', url: this.getProductsUrl(), withCredentials: true })
                .success(function (data, status, headers, config) {
                    successCallback(data, status, headers, config);
                })
                .error(function (data, status, headers, config) {
                    errorCallback()
                });
        },
        checkSessionUrl: function () {
            var getUrl = this.getBaseUrl() + 'check/v3';
            return getUrl;
        },
        checkSession: function (successCallback, errorCallback) {
            $http({ method: 'GET', url: this.checkSessionUrl(), withCredentials: true})
                .success(function (data, status, headers, config) {
                    successCallback(data, status, headers, config);
                })
                .error(function (data, status, headers, config) {
                    errorCallback();
                });
        },
        postLoginUrl: function () {
            var getUrl = this.getBaseUrl() + 'login/v3';
            return getUrl;
        },
        postLogin: function (login, successCallback, errorCallback) {
            $http({ method: 'POST', url: this.postLoginUrl(), data: login, withCredentials: true})
                .success(function (data, status, headers, config) {
                    successCallback(data, status, headers, config);
                })
                .error(function (data, status, headers, config) {
                    errorCallback();
                });
        },
        deleteLogoutUrl: function () {
            var getUrl = this.getBaseUrl() + 'logout/v3';
            return getUrl;
        },
        deleteLogout: function (successCallback, errorCallback) {
            $http({ method: 'DELETE', url: this.deleteLogoutUrl(), withCredentials: true })
                .success(function (data, status, headers, config) {
                    successCallback(data, status, headers, config);
                })
                .error(function (data, status, headers, config) {
                    errorCallback();
                });
        }
    };
}]);



