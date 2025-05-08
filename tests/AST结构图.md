var-decl
├── i32
└── var-array
    ├── a
    ├── array-index
    │   ├── const-exp → 3
    │   └── const-exp → 2
    └── array-init
        ├── =
        │   └── exp → 1
        ├── =
        │   └── exp → 2
        ├── array-init
        │   ├── =
        │   │   └── exp → 3
        │   └── =
        │       └── exp → 4
        └── =
            └── exp → 5


assign-stmt
├── array-access
│   ├── B
│   ├── exp
│   │   └── const-exp → 2
│   └── exp
│       └── const-exp → 1
└── exp
    └── const-exp → 8


