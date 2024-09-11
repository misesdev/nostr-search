"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.listUsers = void 0;
const disk_1 = require("../filesytem/disk");
const listUsers = (pool) => __awaiter(void 0, void 0, void 0, function* () {
    const pubkeys = [];
    const fileUsers = new disk_1.FileSystem("users.db");
    const filePubkeys = new disk_1.FileSystem("pubkeys.db");
    yield filePubkeys.readLines(line => pubkeys.push(line));
    let skipe = 200;
    for (let i = 0; i <= pubkeys.length; i += skipe) {
        let authors = pubkeys.slice(i, i + skipe);
        let events = yield pool.fechEvents({
            authors: authors,
            limit: skipe,
            kinds: [0]
        });
        console.log("events:", events.length);
        events.forEach(event => {
            try {
                let user = JSON.parse(event.content);
                user["pubkey"] = event.pubkey;
                fileUsers.writeLine(JSON.stringify(user));
            }
            catch (_a) { }
        });
    }
    console.log("found users:", pubkeys.length);
});
exports.listUsers = listUsers;
