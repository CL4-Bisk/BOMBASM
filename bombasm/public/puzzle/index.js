const title         = document.querySelector(".title");
const subtitle      = document.querySelector(".subtitle");
const currentBit    = document.querySelector(".current-bitstring-screen");
const targetBit     = document.querySelector(".target-section .screen");
const previousOp    = document.querySelector(".prev-operation-section .screen");
const opcount       = document.querySelector(".operation-count-section .screen")
const opButtons     = document.querySelector(".main-buttons");

(async () => {
    const params = new URLSearchParams(document.location.search);
    const lvl = params.get("level");

    const response = await fetch('./../json/puzzle-levels.json'); 
    const puzzles = await response.json();
    let puzzle;
    puzzles.forEach(p => 
        (p.number == lvl) ? puzzle = p : {}
    )

    title.textContent       = puzzle.title;
    subtitle.textContent    = puzzle.subtitle;
    currentBit.textContent  = puzzle.start_bitstring; 
    targetBit.textContent   = puzzle.goal_bitstring;
    opcount.textContent     = puzzle.op_count;

    puzzle.operations.forEach(op => {
        const button = document.createElement("button");
        button.className = "operation-btn";
        button.textContent = op;
        button.addEventListener("click", () => doBitOperation(op));
        opButtons.appendChild(button);
    });

    function doBitOperation(op) {
        [operator, operand] = op.split(" ");

        let newString = ""; 
        switch (operator) {
        case "AND": 
            for (let i = 0; i < puzzle.bitstring_length; i++) {
                newString += (operand[i] & currentBit.textContent[i]);
            }
            break;
        case "OR": 
            for (let i = 0; i < puzzle.bitstring_length; i++) {
                newString += (operand[i] | currentBit.textContent[i]);
            }
            break;
        case "NOT": 
            for (let i = 0; i < puzzle.bitstring_length; i++) {
                newString += (currentBit.textContent[i] ^ 1);
            }
            break;
        case "XOR": 
            for (let i = 0; i < puzzle.bitstring_length; i++) {
                newString += (operand[i] ^ currentBit.textContent[i]);
            }
            break;
        
        case "SHL": {
            let shift = parseInt(operand);
            newString = currentBit.textContent.slice(shift) + "0".repeat(shift);
            break;
        }

        case "SHR": { 
            let shift = parseInt(operand);
            newString = "0".repeat(shift) + currentBit.textContent.slice(0, puzzle.bitstring_length - shift);
            break;
        }

        case "ROL": {
            let shift = parseInt(operand);
            const actualShift = shift % puzzle.bitstring_length;
            newString = currentBit.textContent.slice(actualShift) + currentBit.textContent.slice(0, actualShift);
            break;
        }

        case "ROR": {
            let shift = parseInt(operand);
            const actualShift = shift % puzzle.bitstring_length;
            newString = currentBit.textContent.slice(-actualShift) + currentBit.textContent.slice(0, -actualShift);
            break;
        }
        }
        
        currentBit.textContent = newString;
        opcount.textContent--;

        if (currentBit.textContent == targetBit.textContent) {
            const modalOverlay = document.querySelector(".modal-overlay");
            const victoryModal = document.querySelector(".victory-modal");
            modalOverlay.classList.remove("hidden");
            victoryModal.classList.remove("hidden");
        
        } else if (opcount.textContent == 0) {
            const modalOverlay = document.querySelector(".modal-overlay");
            const gameOverModal = document.querySelector(".gameover-modal");
            modalOverlay.classList.remove("hidden");
            gameOverModal.classList.remove("hidden");                    
        }
    }
})();

const resetLevel = document.querySelectorAll(".reset-btn");
const toPuzzlePage = document.querySelectorAll(".to-puzzle-btn");

resetLevel.forEach(btn => {
    btn.addEventListener("click", () => {
        window.location.reload();
    });
})  
toPuzzlePage.forEach(btn => {
    btn.addEventListener("click", () => {
        window.location.href = "./../puzzle-levels/"
    });
})