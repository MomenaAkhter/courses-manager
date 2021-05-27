# Getting Started

## Building

The project is based on CMake for building, and thus, follows the same rules as any other CMake project.

To build the project, a typical command would look like this:

```bash
cmake . -G Ninja -B build && cmake --build build
```

This would use "Ninja" as the generator and "build" as the build directory.

The generic version of the above command would be this, where `<build-dir>` is the build directory and `<generator>` is the generator:

```bash
cmake . -G <generator> -B <build-dir> && cmake --build <build-dir>
```

## Running

Run the following generic command for running the built program, where `<build-dir>` represents the build directory:

```bash
./<build-dir>/main
```

# Extracting Course Information from NSU RDS

Run this code in the browse console inside NSU RDS's `Degree` > `View Only` page.

```javascript
(()=>{const e=document.querySelectorAll("table"),t=e[3],n=e[4],o=e[5],c=e[6],r=e[7];function a(e){const t=[];return e.querySelectorAll("tbody tr").forEach((function(e){const n=e.querySelectorAll("td");0!==n.length&&t.push({name:n[0].innerHTML,title:n[1].innerHTML,gradePoints:parseFloat(n[4].innerHTML),creditsCounted:parseFloat(n[5].innerHTML),creditsPassed:parseFloat(n[6].innerHTML)})})),t}const l=a(t).concat(a(n)).concat(a(o)).concat(a(c)).concat(a(r));let s="";l.forEach((function(e){s+=[e.name,e.title,"Summer 2021",e.creditsCounted,e.creditsPassed,e.gradePoints].join(", ")+"\n"})),console.log(s)})();
```
