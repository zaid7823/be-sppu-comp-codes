// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.0;

contract Bank {
    mapping (address=>uint) public userAcc;
    mapping(address=>bool) public userExists;
    // ==========================
    function createAccount(uint amount) public returns (string memory) {
        require(!userExists[msg.sender], "Account already exists");
        userAcc[msg.sender] = amount;
        userExists[msg.sender] = true;  // confirms that account was created
        return "Account Created successfully!";
    }
    // ==========================
    function deposit() public payable returns (string memory) {
        require(userExists[msg.sender], "Account does not exist");
        require(msg.value > 0, "Deposit amount should be greater than 0");
        userAcc[msg.sender] += msg.value;
        return "Amount deposited successfully!";
    }
    // ==========================
    function withdraw(uint amount) public payable returns (string memory) {
        require(userExists[msg.sender], "Account does not exist");
        require(userAcc[msg.sender] > amount, "Insufficient balance");
        // user cannot withdraw if the amount to withdraw (amount) is more than in the bank (userAcc[msg.sender])

        require(amount > 0, "Invalid number");  // amount can't be zero or negative

        userAcc[msg.sender] -= amount;
        payable(msg.sender).transfer(amount);   // transfer money to user's address
        return "Amount withdrawn";
    }
    // ==========================
    function checkBalance() public view returns (uint) {
        return userAcc[msg.sender];
    }
}
