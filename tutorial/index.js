TutorialLevelsModule().then((Module) => {
    const getTutorialCount      = Module.cwrap("getTutorialLevelCount", "number", []);
    const getLevelTitle = Module.cwrap("getTutorialLevelTitle", "string", ["number"])
    const getLevelOperator = Module.cwrap("getTutorialLevelOperator", "string", ["number"]) 
    const getBitwidth         = Module.cwrap("getTutorialLevelBitWidth", "number", ["number"]);
    const getStartBitstring   = Module.cwrap("getTutorialLevelStartBitstring", "string", ["number"]);
    const getDescription       = Module.cwrap("getTutorialLevelDescription", "string", ["number"]);
    const getOpCount          = Module.cwrap("getTutorialLevelOperationCount", "number", ["number"]);
    const getOperations       = Module.cwrap("getTutorialLevelOperations", "string", ["number"]);

    const title         = document.querySelector(".title");
    const subtitle      = document.querySelector(".subtitle");
    const currentBit    = document.querySelector(".current-bitstring-screen");
    const description   = document.querySelector(".description-section .screen");
    const opButtons     = document.querySelector(".main-buttons");

    const params = new URLSearchParams(document.location.search);
    const index = parseInt(params.get("level"));


    title.textContent       = getLevelTitle(index);
    subtitle.textContent    = getLevelOperator(index);
    currentBit.textContent  = getStartBitstring(index); 
    description.textContent = getDescription(index);

    GameLogicModule().then((Module) => { 
        const doBitOperation = Module.cwrap(
            "bitStringOperations", "string", ["string", "string", "string", "number"]
        );
        
        const operations = getOperations(index).split(",");
        operations.forEach(op => {
            const button = document.createElement("button");
            button.className = "operation-btn";
            button.textContent = op;

            let [operation, operand] = op.split(" ");
            if (operand === undefined) operand = "";

            button.addEventListener("click", () => { 
                currentBit.textContent = doBitOperation(
                    currentBit.textContent, 
                    operand,
                    operation,
                    getBitwidth(index)
                );
                opcount.textContent = parseInt(opcount.textContent) - 1;
                
            });

            opButtons.appendChild(button);
        });

        
    });

    const resetLevel = document.querySelectorAll(".reset-btn");
    resetLevel.forEach(btn => {
        btn.addEventListener("click", () => {
            window.location.reload();
        });
    })  

    const toPuzzlePage = document.querySelectorAll(".to-puzzle-btn");
    toPuzzlePage.forEach(btn => {
        btn.addEventListener("click", () => {
            window.location.href = "./../puzzle-levels/"
        });
    })
});

