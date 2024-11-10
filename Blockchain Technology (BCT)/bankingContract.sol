// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.0;

contract Bank {
    mapping (address => uint) public userAcc;
    mapping (address => bool) public userExists;
    mapping (address => Transaction[]) public transactionHistory;

    struct Transaction {
        string action;    // "Deposit" or "Withdrawal"
        uint amount;      // amount of transaction
        uint timestamp;   // timestamp of transaction
    }

    // Modifier to check if account exists
    modifier onlyAccountHolder() {
        require(userExists[msg.sender], "Account does not exist");
        _;
    }

    // Modifier to check for positive amounts
    modifier onlyPositiveAmount(uint amount) {
        require(amount > 0, "Amount must be greater than zero");
        _;
    }

    // Create an account with an initial deposit amount
    function createAccount(uint initialDeposit) public onlyPositiveAmount(initialDeposit) returns (string memory) {
        require(!userExists[msg.sender], "Account already exists");
        
        userAcc[msg.sender] = initialDeposit;
        userExists[msg.sender] = true;
        transactionHistory[msg.sender].push(Transaction("Account Creation", initialDeposit, block.timestamp));
        
        return "Account created successfully!";
    }

    // Deposit funds into the user's account
    function deposit() public payable onlyAccountHolder onlyPositiveAmount(msg.value) returns (string memory) {
        userAcc[msg.sender] += msg.value;
        transactionHistory[msg.sender].push(Transaction("Deposit", msg.value, block.timestamp));
        
        return "Amount deposited successfully!";
    }

    // Withdraw funds from the user's account
    function withdraw(uint amount) public onlyAccountHolder onlyPositiveAmount(amount) returns (string memory) {
        require(userAcc[msg.sender] >= amount, "Insufficient balance");
        
        userAcc[msg.sender] -= amount;
        payable(msg.sender).transfer(amount);
        transactionHistory[msg.sender].push(Transaction("Withdrawal", amount, block.timestamp));
        
        return "Amount withdrawn successfully!";
    }

    // Check the balance of the user's account
    function checkBalance() public view onlyAccountHolder returns (uint) {
        return userAcc[msg.sender];
    }

    // Close the user's account and withdraw all funds
    function closeAccount() public onlyAccountHolder returns (string memory) {
        uint closingBalance = userAcc[msg.sender];
        userAcc[msg.sender] = 0;
        userExists[msg.sender] = false;
        
        payable(msg.sender).transfer(closingBalance);
        transactionHistory[msg.sender].push(Transaction("Account Closed", closingBalance, block.timestamp));
        
        return "Account closed and balance withdrawn successfully!";
    }

    // Get transaction history for the user's account
    function getTransactionHistory() public view onlyAccountHolder returns (Transaction[] memory) {
        return transactionHistory[msg.sender];
    }
}
