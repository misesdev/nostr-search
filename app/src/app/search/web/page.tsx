import { Suspense } from 'react';
import LoadingWeb from './loading';
import WebSearch from '@/components/search/WebSearch';
import { SearchParams } from '@/types/types';
import { defaultPubkey } from '@/constants';

const WebSearchPage = async ({ searchParams }: { searchParams: SearchParams }) => {

    const pubkey = searchParams.pubkey ?? defaultPubkey;
    const searchTerm = searchParams.searchTerm;

    return (
        <Suspense fallback={<LoadingWeb />}>
            <WebSearch pubkey={pubkey} searchTerm={searchTerm} />
        </Suspense>
    )
}

export default WebSearchPage
