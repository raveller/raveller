USE WEBAPI2015;

IF EXISTS (SELECT * FROM sysobjects WHERE id = OBJECT_ID( 'dbo.Config'))
	BEGIN
		PRINT 'Dropping Table dbo.Config';
		DROP TABLE dbo.Config;
	END
GO

CREATE TABLE dbo.Config (
	IDX bigint PRIMARY KEY IDENTITY(1,1),
	Name varchar(50),
	Value varchar(200)
);
GO

INSERT INTO dbo.Config (Name, Value)
SELECT 'CredentialSalt','k3mFGe9i98*3r#q' UNION ALL
SELECT 'Version','WebAPI2015 2.0';
GO

IF EXISTS (SELECT * FROM sysobjects WHERE id = OBJECT_ID( 'dbo.Account'))
	BEGIN
		PRINT 'Dropping Table dbo.Account';
		DROP TABLE dbo.Account;
	END
GO

CREATE TABLE dbo.Account (
	IDX bigint PRIMARY KEY IDENTITY(1,1),
	UserId varchar(40),
	PassHash varchar(100),
	UserRole int,
	Active bit
);
GO

IF EXISTS (SELECT * FROM sysobjects WHERE id = OBJECT_ID( 'dbo.UserRoleLookup'))
	BEGIN
		PRINT 'Dropping Table dbo.UserRoleLookup';
		DROP TABLE dbo.UserRoleLookup;
	END
GO

CREATE TABLE dbo.UserRoleLookup (
	[Role]        int,
	[Description] varchar(40)
	);
GO

INSERT INTO dbo.UserRoleLookup ([Role], [Description])
SELECT 0, 'Shopper' UNION ALL  
SELECT 100, 'Sales' UNION ALL
SELECT 1000, 'Manager' UNION ALL
SELECT 10000, 'Administrator';
GO

IF EXISTS (SELECT * FROM sysobjects WHERE id = OBJECT_ID( 'dbo.demosp_AddAccount'))
	BEGIN
		PRINT 'Dropping Procedure dbo.demosp_AddAccount';
		DROP PROCEDURE dbo.demosp_AddAccount;
	END
GO


CREATE PROCEDURE dbo.demosp_AddAccount
	@userId varchar(40),
	@passHash varchar(100),
	@userRole int
AS
BEGIN
	BEGIN TRANSACTION
	IF NOT EXISTS (SELECT 0 FROM dbo.Account WHERE UserId = @userId)
		INSERT INTO dbo.Account (UserId, PassHash, UserRole, Active)
		SELECT @userId, @passHash, @userRole, 1
	COMMIT TRANSACTION
END
GO

IF EXISTS (SELECT * FROM sysobjects WHERE id = OBJECT_ID( 'dbo.Product'))
	BEGIN
		PRINT 'Dropping Table dbo.Product';
		DROP TABLE dbo.Product;
	END
GO

CREATE TABLE dbo.Product (
	IDX bigint PRIMARY KEY IDENTITY(1,1),
	Title varchar(80),
	ProductCode varchar(30) UNIQUE,
	Price decimal NOT NULL,
	Quantity int NOT NULL,
	Description varchar (400),
	Active bit NOT NULL,
	Released bit NOT NULL
);
GO

INSERT INTO dbo.Product (ProductCode, Price, Quantity, Active, Released, Title, [Description])
SELECT 'PREMWAF2000',60.0,20,1,1,'Premium Waffle','The best of what we have to offer.  Waffle with Syrup and Butter and Whipped Cream !' UNION ALL  
SELECT 'EWAF2000',10.0,41,1,1,'Waffle','Entry Level Waffle for the Waffling novice' UNION ALL
SELECT 'WAF',15.0,38,1,1,'Waffle + Butter','Waffle Plus Butter' UNION ALL
SELECT 'WAFSUPR3323',23.0,99,1,1,'Waffle Supreme','Waffle with Butter and Maple Syrup, our best seller!' UNION ALL
SELECT 'ZMBEEWAF2000',35.0,20,1,0,'Zombie Waffle','This waffle has it all!  Waffles!  Butter!  Syrup!  Gummy Worms!' UNION ALL
SELECT 'BRNTWAFXXXX',5.0,3000,0,1,'Burnt Waffle','Burnt waffles have many uses!  Take advantages of our mistakes!  Buy today!';
GO


IF EXISTS (SELECT * FROM sysobjects WHERE id = OBJECT_ID( 'dbo.demosp_UpsertProduct'))
	BEGIN
		PRINT 'Dropping Procedure dbo.demosp_UpsertProduct';
		DROP PROCEDURE dbo.demosp_UpsertProduct;
	END
GO

CREATE PROCEDURE dbo.demosp_UpsertProduct
	@productCode varchar(30),
	@title varchar(80) = NULL,
	@price decimal = NULL,
	@description varchar (400) = NULL,
	@released bit = NULL
AS
BEGIN
	BEGIN TRANSACTION
	IF EXISTS (SELECT 0 FROM dbo.Product WHERE ProductCode = @productCode)
		UPDATE dbo.Product SET
		   Title = COALESCE(@title, Title),
		   [Description] = COALESCE(@description, [Description]),
		   Price = COALESCE(@price, Price),
		   Released = COALESCE(@released, Released)
	    WHERE ProductCode = @productCode

	ELSE
		INSERT INTO dbo.Product (ProductCode, Title, [Description], Price, Quantity, Active, Released)
		SELECT @productCode,
			   ISNULL(@title, 'To Be Announced'),
			   ISNULL(@description, 'Description forthcoming'),
		       ISNULL(@price, 999999.99),
			   0,
			   1,
			   ISNULL(@released, 0)
		 
	COMMIT TRANSACTION
END
GO

IF EXISTS (SELECT * FROM sysobjects WHERE id = OBJECT_ID( 'dbo.demosp_DeactivateProduct'))
	BEGIN
		PRINT 'Dropping Procedure dbo.demosp_DeactivateProduct';
		DROP PROCEDURE dbo.demosp_DeactivateProduct;
	END
GO

CREATE PROCEDURE dbo.demosp_DeactivateProduct
	@productCode varchar(30)
AS
BEGIN
	BEGIN TRANSACTION
	IF EXISTS (SELECT 0 FROM dbo.Product WHERE ProductCode = @productCode)
		UPDATE dbo.Product SET
		   Active = 0
	    WHERE ProductCode = @productCode

	COMMIT TRANSACTION
END
GO

IF EXISTS (SELECT * FROM sysobjects WHERE id = OBJECT_ID( 'dbo.ActiveSession'))
	BEGIN
		PRINT 'Dropping Table dbo.ActiveSession';
		DROP TABLE dbo.ActiveSession;
	END
GO

CREATE TABLE dbo.ActiveSession (
	IDX         bigint PRIMARY KEY,
	Expiry      datetime,
	Account_IDX bigint,
	UserId      varchar(40)
	);
	GO

	
IF EXISTS (SELECT * FROM sysobjects WHERE id = OBJECT_ID( 'dbo.demosp_ReadProducts'))
	BEGIN
		PRINT 'Dropping Procedure dbo.demosp_ReadProducts';
		DROP PROCEDURE dbo.demosp_ReadProducts;
	END
GO

CREATE PROCEDURE dbo.demosp_ReadProducts 
	@userRole int = 0
AS
BEGIN
	DECLARE @active bit, @released bit

	if @UserRole > 9999
		SET @released = 0
	ELSE
		SET @released = 1

	if @UserRole > 999
		SET @active = 0
	ELSE
		SET @active = 1

	SELECT IDX, Title, ProductCode, Price, Quantity, Description, Active, Released
	  FROM dbo.Product WITH (NOLOCK)
    WHERE Active IN (1, @active) AND Released IN (1, @released);
END
GO


	
IF EXISTS (SELECT * FROM sysobjects WHERE id = OBJECT_ID( 'dbo.Sale'))
	BEGIN
		PRINT 'Dropping Table dbo.Sale';
		DROP TABLE dbo.Sale;
	END
GO

CREATE TABLE dbo.Sale (
	IDX          bigint PRIMARY KEY IDENTITY(1,1),
	Total        money,
	PurchaseTime datetime
	);
GO

	
IF EXISTS (SELECT * FROM sysobjects WHERE id = OBJECT_ID( 'dbo.SaleItem'))
	BEGIN
		PRINT 'Dropping Table dbo.SaleItem';
		DROP TABLE dbo.SaleItem;
	END
GO

CREATE TABLE dbo.SaleItem (
	IDX          bigint PRIMARY KEY IDENTITY(1,1),
	Sale_IDX     bigint,
	Product_IDX  bigint,
	Quantity     int
	);
