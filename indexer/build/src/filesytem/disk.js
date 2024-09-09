"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.FileSystem = void 0;
const fs = require("fs");
class FileSystem {
    constructor(fileName) {
        if (fileName.length < 2)
            throw Error("invalid file name");
        this.file = fs.createWriteStream(fileName, { flags: "a" });
    }
    writeLine(line) {
        this.file.write(`${line}\n`);
    }
}
exports.FileSystem = FileSystem;
