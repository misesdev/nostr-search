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
const RelayPool_1 = require("./src/modules/RelayPool");
const Relays_1 = require("./src/constants/Relays");
const disk_1 = require("./src/filesytem/disk");
const utils_1 = require("./src/utils");
const author = "55472e9c01f37a35f6032b9b78dade386e6e4c57d80fd1d0646abb39280e5e27";
const main = () => __awaiter(void 0, void 0, void 0, function* () {
    let fileUsers = new disk_1.FileSystem("./data/users.db");
    let filePubkeys = new disk_1.FileSystem("./data/pubkeys.db");
    const pool = new RelayPool_1.RelayPool(Relays_1.relays);
    yield pool.connect();
    let userEvent = yield pool.fechUser(author);
    let pubkeys = (0, utils_1.getPubkeys)(userEvent);
    pubkeys.push(userEvent.pubkey);
    let skip = 10;
    for (let i = 0; pubkeys.length < 20000; i += skip) {
        let events = yield pool.fechEvent({
            authors: pubkeys.slice(i, i + skip),
            kinds: [3],
            limit: skip
        });
        if (events.length > 0) {
            events.forEach(event => {
                console.log(`${event.tags.length} follows:`, event.pubkey.substring(0, 15));
                let npubs = (0, utils_1.getPubkeys)(event).filter(npub => !pubkeys.includes(npub));
                npubs.forEach(pub => pubkeys.push(pub));
            });
        }
        else
            console.log("not found");
        skip++;
    }
    pubkeys.forEach(pubkey => filePubkeys.writeLine(pubkey));
    skip = 100;
    for (let i = 0; i < pubkeys.length; i += skip) {
        let events = yield pool.fechEvent({
            authors: pubkeys.slice(i, i + skip),
            kinds: [0],
            limit: skip
        });
        if (events.length > 0) {
            console.log("found users:", events.length);
            events.forEach(event => fileUsers.writeLine(event.content));
        }
        else
            console.log("not found users");
    }
    console.log("found users from nostr:", pubkeys.length);
});
main();
