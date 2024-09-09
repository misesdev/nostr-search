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
const author = "55472e9c01f37a35f6032b9b78dade386e6e4c57d80fd1d0646abb39280e5e27";
const main = () => __awaiter(void 0, void 0, void 0, function* () {
    let pubkeys = [author];
    let file = new disk_1.FileSystem("pubkeys.db");
    const pool = new RelayPool_1.RelayPool(Relays_1.relays, author);
    yield pool.connect();
    //let user = await pool.fetchUser(author);
    //pubkeys.push(user.pubkey)
    ///file.writeLine(nostrEvent.content)
    let key = 0;
    while (pool.pubkeys.length < 5000) {
        console.log("search event from key", pool.pubkeys[key]);
        yield pool.fechEvent({
            authors: [pool.pubkeys[key]],
            kinds: [3],
            limit: 1
        });
        //let npubs = getPubkeys(events[0]).filter(f => !pubkeys.includes(f))
        //console.log("npubs", npubs.length)
        //npubs.forEach(pub => pubkeys.push(pub));
        //pubkeys = [...pubkeys, ...npubs];
        key++;
    }
    pool.pubkeys.forEach(pubkey => file.writeLine(pubkey));
    console.log("found users from nostr:", pool.pubkeys);
});
main();
