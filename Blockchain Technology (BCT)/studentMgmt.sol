// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.0;

contract StudentMgmt {
    
    // Define a Student structure
    struct Student {
        int stud_id;
        string stud_name;
        string dept;
    }
    
    // Array to store all Student structures
    Student[] private students;

    // Adds a new student's details to the array
    function addStudentDetails(int id, string memory name, string memory dept) public returns (string memory) {
        // Check for duplicate student ID
        for (uint i = 0; i < students.length; i++)  {
            if (students[i].stud_id == id) {
                return "Duplicate records cannot be added";
            }
        }
        
        // If no duplicate is found, create and add the new student record
        Student memory newStudent = Student(id, name, dept);
        students.push(newStudent);
        
        return "Student added successfully!";
    }

    // Retrieves a student's details by ID
    function getStudentDetails(int id) public view returns (string memory, string memory) {
        // Iterate over the students array to find the student with matching ID
        for (uint i = 0; i < students.length; i++) {
            if (students[i].stud_id == id) {
                return (students[i].stud_name, students[i].dept);
            }
        }
        
        // If student not found, return default message
        return ("Not Found", "Not Found");
    }

    // Deletes a student's details by ID
    function deleteStudentDetails(int id) public returns (string memory) {
        for (uint i = 0; i < students.length; i++) {
            if (students[i].stud_id == id) {
                // Move the last element into the place of the element to delete
                students[i] = students[students.length - 1];
                students.pop(); // Remove the last element, reducing the array size
                return "Student details successfully deleted!";
            }
        }
        
        // If student ID is not found, return default message
        return "Student ID not found";
    }

    // Returns the total number of students currently stored
    function getTotalStudents() public view returns (uint) {
        return students.length;
    }
    
    // Fallback function to handle unexpected Ether sent to the contract
    fallback() external payable {
        // This contract does not accept Ether, so it simply reverts the transaction
        revert("This contract does not accept Ether.");
    }
}
