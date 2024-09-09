import * as fs from 'fs'

export class FileSystem {
    private file: fs.WriteStream;

    constructor(fileName: string) {
        if(fileName.length < 2) 
            throw Error("invalid file name")
        this.file = fs.createWriteStream(fileName, { flags: "a" });
    }
 
    public writeLine(line: string) {
        this.file.write(`${line}\n`)
    }
}

