<div align="center"> 
    <img src="assets/logo.svg" height=312>
</div>

<br/>

<p align="center">
    A C++23 library providing mutex protection for any object
</p>


> [!NOTE]
> See versions <`3.0` for C++20 support!

## 📦 Installation

* Using [CPM](https://github.com/cpm-cmake/CPM.cmake)
  ```cmake
  CPMFindPackage(
    NAME           lockpp
    VERSION        3.0
    GIT_REPOSITORY "https://github.com/Curve/lockpp"
  )
  ```

* Using FetchContent
  ```cmake
  include(FetchContent)

  FetchContent_Declare(lockpp GIT_REPOSITORY "https://github.com/Curve/lockpp" GIT_TAG v3.0)
  FetchContent_MakeAvailable(lockpp)

  target_link_libraries(<target> cr::lockpp)
  ```

## 📃 Usage

```cpp
lockpp::lock<std::string> var("Test");

// Read only access
{
    auto locked = var.read();
    assert(!locked->empty());
}

// Write access
{
    auto locked = var.write();

    *write_access = "assignment";
    locked->clear();
}

// One time access
var.assign("another assignment");
assert(var.copy() == "another assignment");
```

_lockpp_ also allows you to [supply the mutex to be used](tests/custom-mutex.cpp) as well [as custom locks](tests/custom-lock.cpp) _(i.e `std::unique_lock`, `std::lock_guard`)_.

> For more examples see [tests](tests)
