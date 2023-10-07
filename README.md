omgopasscc
==========

single-header C++11 version of [omgopass](https://github.com/omgovich/omgopass) library.

Made it just-for-fun without maintain. 

Sample
------

Run with default config

```c
#include "omgopasscc.h"

...
    
std::cout << "result: " << omgopasscc::generate() << "\n";

/// result: Wo3-Abo8-Viz2
```

Customize by struct config
```c
#include "omgopasscc.h"

...
omgopasscc::config cfg;
cfg.separators=""
std::cout << "config: " << omgopasscc::to_string(cfg) << "\n";
std::cout << "result: " << omgopasscc::generate(cfg) << "\n";

/// result: Lim2So7Xo1
```


